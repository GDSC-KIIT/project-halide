#ifndef __GLOBAL_DESCRIPTOR_TABLE_H
#define __GLOBAL_DESCRIPTOR_TABLE_H

namespace GLOBAL_DESCRIPTOR_TABLE {
    class GlobalDescriptorTable {
        public:
        class SegmentDescriptor {
            private:
            unsigned short lower_limit;
            unsigned short lower_base;
            unsigned char higher_base;
            unsigned char type;
            unsigned char flags_higher_limit;
            unsigned char base_vhi;

            public:
            SegmentDescriptor(unsigned int base, unsigned int limit, unsigned char type);
            unsigned int Base();
            unsigned int Limit();
        }__attribute__((packed));
        SegmentDescriptor null;
        SegmentDescriptor unused;
        SegmentDescriptor code;
        SegmentDescriptor data;
        public:
        GlobalDescriptorTable();
        ~GlobalDescriptorTable();
        unsigned short codeSegment();
        unsigned short dataSegment();
    };
}

#endif

// * Postfix is converting from eqn to stack eqvalent
// * Opereator precendence > then prev pop